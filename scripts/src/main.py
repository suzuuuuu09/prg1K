import os
import zipfile as zf

def get_file_names(folder_path):
    # フォルダ内のファイル名を取得する
    file_names = os.listdir(folder_path)
    return file_names

def create_zip(folder_path, zip_name):
    with zf.ZipFile(zip_name, "w") as zip_file:
        files = get_file_names(folder_path)
        
        for file in files:
            file_path = os.path.join(folder_path, file)
            if os.path.isfile(file_path):
                zip_file.write(file_path, file)

if __name__ == "__main__":
    folder_path = "../src/03"
    zip_name = "output.zip"
    
    create_zip(folder_path, zip_name)
    print(f"ZIP file '{zip_name}' has been created successfully.")