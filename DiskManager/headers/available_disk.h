void available_disk()
{
    system("lsblk -o NAME,SIZE,TYPE,MOUNTPOINT | grep -E '^<device_name>\s|─'");
}