using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Windows.Storage;

namespace SP_Laba_8
{
    public class FolderData
    {
        //current folder
        StorageFolder root_folder;

        IReadOnlyList<StorageFile> fileList;
        IReadOnlyList<StorageFolder> folderList;

        //item source for listview
        internal ObservableCollection<FolderContent> ViewContentList;

        public StorageFolder Root()
        {
            return root_folder;
        }
        public FolderData()
        {
            root_folder = Windows.ApplicationModel.Package.Current.InstalledLocation;
            ViewContentList = new ObservableCollection<FolderContent>();
        }
        public FolderData(StorageFolder r_folder)
        {
            root_folder = r_folder;
            ViewContentList = new ObservableCollection<FolderContent>();
        }
        internal bool SubfolderSearch(FolderContent fc)
        {
            foreach (StorageFolder folder in folderList)
            {
                if (folder.Name == fc.Name)
                {
                    root_folder = folder;
                    return true;
                }
            }
            return false;
        }
        public async void PopulateViewList()
        {

            ViewContentList.Clear();

            fileList = await root_folder.GetFilesAsync();
            folderList = await root_folder.GetFoldersAsync();

            foreach (StorageFolder folder in folderList)
            {
                ViewContentList.Add(new FolderContent()
                {
                    Name = folder.Name,
                    DateCreated = folder.DateCreated.UtcDateTime.ToString(@"MM\/dd\/yyyy HH:mm"),
                    FileType = "Folder",
                    Size = "N/A"
                });
            }

            foreach (StorageFile file in fileList)
            {
                var props = await file.GetBasicPropertiesAsync();

                ViewContentList.Add(new FolderContent()
                {
                    Name = file.Name,
                    DateCreated = file.DateCreated.UtcDateTime.ToString(@"MM\/dd\/yyyy HH:mm"),
                    FileType = "File",
                    Size = CountSize(props.Size)
                });
            }
        }
        private string CountSize(ulong fileSize)
        {
            ulong croppedSize = fileSize;
            if (croppedSize >= 1000000)//above 1 mil of bytes
            {
                croppedSize /= 1000000;
                return croppedSize + " MB";
            }
            else if (croppedSize >= 1000)
            {
                croppedSize /= 1000;
                return croppedSize + " kB";
            }
            return croppedSize + " B";
        }
    }
    //for data storage (about files and subfolders in current folder)
    internal class FolderContent
    {
        public string Name { get; set; }
        public string Size { get; set; }
        public string DateCreated { get; set; }
        public string FileType { get; set; }
    }
}
