from pathlib import Path

def delete_exe_files(parent_directory_path):
    # Convert string path to a Path object
    parent_dir = Path(parent_directory_path)
    
    # Check if the directory actually exists
    if not parent_dir.exists() or not parent_dir.is_dir():
        print(f"Error: '{parent_directory_path}' is not a valid directory.")
        return

    print(f"Scanning '{parent_dir.resolve()}' for .exe files...\n")
    deleted_count = 0

    # rglob stands for "recursive glob" - it searches all subdirectories
    # We use case-insensitive matching by checking lower-case suffix
    for file_path in parent_dir.rglob("*"):
        if file_path.is_file() and file_path.suffix.lower() == '.exe':
            try:
                print(f"Deleting: {file_path}")
                file_path.unlink()  # Deletes the file
                deleted_count += 1
            except Exception as e:
                print(f"Failed to delete {file_path}. Reason: {e}")

    print(f"\nTask complete. Total .exe files deleted: {deleted_count}")

# --- Usage Example ---
if __name__ == "__main__":
    # Replace this with your actual target directory
    # Use raw string (r"path") on Windows to avoid backslash escaping issues
    target_directory = r"C:\Users\User\Documents\MMU_STUDIES\Studies\SecondYearThirdSem\Software_Design\TestCodeBase"
    
    # Dry-run warning: It's always smart to back up important folders before running!
    delete_exe_files(target_directory)