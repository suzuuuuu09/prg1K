import { readdir } from 'fs/promises';

async function listDirectoryContents(): Promise<void> {
  try {
    const files: string[] = await readdir("../src/01");
    files.sort((a, b) => a.localeCompare(b));
    files.forEach((x) => console.log(x));
  } catch (error) {
    console.error("ディレクトリの読み取りに失敗しました:", error);
  }
}

// if __name__ == "__main__":みたいなやつ
if (require.main == module) {
  listDirectoryContents();
}