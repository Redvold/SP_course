using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x419

namespace SP_Laba_8
{
    public sealed partial class MainPage : Page
    {
        //stores current folder and it's content, handels operations
        FolderData folder_handler;

        public MainPage()
        {
            this.InitializeComponent();
            folder_handler = new FolderData();
            listView.ItemsSource = folder_handler.ViewContentList;
        }

        private async void open_folder(object sender, RoutedEventArgs e)
        {
            var folderPicker = new FolderPicker
            {
                SuggestedStartLocation = PickerLocationId.Desktop
            };
            folderPicker.FileTypeFilter.Add("*");

            StorageFolder folder = await folderPicker.PickSingleFolderAsync();
            if (folder != null)
            {
                Windows.Storage.AccessCache.StorageApplicationPermissions.
                FutureAccessList.AddOrReplace("PickedFolderToken", folder);
                folder_handler = new FolderData(folder);
                folder_handler.PopulateViewList();
                listView.ItemsSource = folder_handler.ViewContentList;
            }
        }
        private async void create_folder(object sender, RoutedEventArgs e)
        {
            try
            {

                string NewName = folderName_tb.Text;
                await folder_handler.Root().CreateFolderAsync(NewName);
                folder_handler.PopulateViewList();
                listView.ItemsSource = folder_handler.ViewContentList;
                Error_tb.Text = "";
            }
            catch (Exception)
            {
                Error_tb.Text = "Can't add folder.";
            }
        }
        private async void delete_click(object sender, RoutedEventArgs e)
        {
            try
            {
                FolderContent subfolder = (FolderContent)(e.OriginalSource as FrameworkElement).DataContext;
                if (subfolder.FileType == "Folder")
                {
                    StorageFolder folder = await folder_handler.Root().GetFolderAsync(subfolder.Name);
                    await folder.DeleteAsync();
                    folder_handler.PopulateViewList();
                    listView.ItemsSource = folder_handler.ViewContentList;
                    Error_tb.Text = "";
                }
            }
            catch (Exception)
            {
                Error_tb.Text = "Can't delete folder.";
            }
        }
        private void subfolder_click(object sender, DoubleTappedRoutedEventArgs e)
        {
            FolderContent subfolder = (FolderContent)listView.SelectedItem;
            if (folder_handler.SubfolderSearch(subfolder))
            {
                folder_handler.PopulateViewList();
                listView.ItemsSource = folder_handler.ViewContentList;
            }
        }

        private void context_menu(object sender, RightTappedRoutedEventArgs e)
        {
            FrameworkElement senderElement = sender as FrameworkElement;
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(senderElement);
            flyoutBase.ShowAt(senderElement);
        }

        private void listView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
