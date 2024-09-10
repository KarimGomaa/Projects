# 📂 Process Monitor Script 

## 📑 Table of Contents

- [📝 Description](#-description)
- [🚀 Usage](#-usage)
- [🔍 Script Overview](#-script-overview)
- [🧪 Example](#-example)
- [🎥 Testing Video](#-testing-video)

## 📝 Description

`process_monitor.sh` is a Bash script designed to organize files within a specified directory. It takes a path to a directory as its argument and sorts the files into subdirectories based on their file extension. The script categorizes files into `txt`, `jpg`, and `pdf` directories, with all other files being moved to a `misc` directory. Additionally, hidden files are also moved to the `misc` directory.

## 🚀 Usage 

To use this script, follow these steps:

1. Open your terminal.
2. Navigate to the directory containing `process_monitor.sh`.
3. Make sure the script has executable permissions:
    ```bash
    chmod +x process_monitor.sh
    ```
4. Run the script with the path to the directory you want to organize:
    ```bash
    ./process_monitor.sh /path/to/directory
    ```

## 🔍 Script Overview 

The script performs the following tasks:

1. **Create Subdirectories**: It creates the following subdirectories in the specified directory:
    - `txt` for text files
    - `jpg` for JPEG image files
    - `pdf` for PDF files
    - `misc` for all other files

2. **Organize Files**:
    - It loops through all files in the specified directory and moves them to their respective subdirectories based on their file extensions.
    - Files with extensions other than `txt`, `jpg`, or `pdf` are moved to the `misc` directory.
  
3. **Handle Hidden Files**:
    - It also processes hidden files (those starting with a dot `.`) and moves them to the `misc` directory.

4. **Completion Message**:
    - Once all files are organized, the script prints "Files organized successfully."

## 🧪 Example 

To organize files in the `/home/user/Documents` directory, you would run:

```bash
./process_monitor.sh /home/user/Documents
```

## 📹 Testing Video

You can view the testing video [here](https://drive.google.com/file/d/1QLjB-xf9sAfKaoWZCzNUnN4y-o5Gt7UI/view?usp=sharing).
