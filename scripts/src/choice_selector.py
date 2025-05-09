import sys
import os
if os.name == 'nt':  # Windows
    from msvcrt import getch
else:  # Mac/Linux
    import tty
    import termios

class ChoiceSelector:
    def __init__(self, menu_options, menu_start_row, menu_selected_index=0):
        self.menu_options = menu_options
        self.menu_selected_index = menu_selected_index
        self.menu_start_row = menu_start_row

    def _get_key_windows(self):
        key = ord(getch())
        if key == 224:  # 特殊キー
            key = ord(getch())
            if key == 75:
                return 'left'
            elif key == 77:
                return 'right'
            else:
                return None
        return 'enter' if key == 13 else None

    def _get_key_unix(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
            if ch == '\x1b':
                ch = sys.stdin.read(2)
                if ch == '[D':
                    return 'left'
                elif ch == '[C':
                    return 'right'
                else:
                    return None
            return 'enter' if ch == '\r' else None
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    def get_key(self):
        return self._get_key_windows() if os.name == 'nt' else self._get_key_unix()

    def display_menu(self):
        # カーソル位置を"select."の後ろに移動
        print(f"\033[{self.menu_start_row};8H", end='', flush=True)  # 8は"select."の長さ + 1
        
        # 選択肢を表示
        for i, option in enumerate(self.menu_options):
            if i == self.menu_selected_index:
                print(f"\033[33m> {option}\033[0m", end=' ', flush=True)
            else:
                print(f"  {option}", end=' ', flush=True)

    def run(self):
        # 画面をクリア
        print("\033[2J\033[H", end='')
        # "select."を表示
        print(f"\033[{self.menu_start_row};1Hselect.", end='', flush=True)
        
        self.display_menu()
        while True:
            key = self.get_key()
            if key == 'left':
                if self.menu_selected_index > 0:
                    self.menu_selected_index -= 1
                    self.display_menu()
            elif key == 'right':
                if self.menu_selected_index < len(self.menu_options) - 1:
                    self.menu_selected_index += 1
                    self.display_menu()
            elif key == 'enter':
                break
        print("\n")
        return self.menu_options[self.menu_selected_index]

if __name__ == "__main__":
    menu_options = ["選択肢1", "選択肢2", "選択肢3"]
    menu_start_row = 1
    selector = ChoiceSelector(menu_options, menu_start_row)
    selected_option = selector.run()
    print(f"選択された項目: {selected_option}")