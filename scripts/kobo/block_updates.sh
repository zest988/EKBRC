#!/bin/sh

# Block automatic updates
mkdir -p /disable_updates
mount --bind /disable_updates /usr/local/upd

# Modify Kobo configuration
sed -i 's/"Upgrade",.*/"Upgrade", "false"/' /mnt/onboard/.kobo/Kobo/Kobo.conf

# Make important files immutable
chattr +i /mnt/onboard/.adds/koreader/koreader.sh
chattr +i /mnt/onboard/.adds/nm/koreader.ini
