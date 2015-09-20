#/bin/sh
# By dayt0n
#
# Written in shell because I am lazy tonight
# Birth: 9/19/15

rePATH="$PWD"

if [[ -f tools/restored_external ]]; then
  :
else
  read -p "restored_external binary not found. Would you like me to build it for you?: " shouldBuild
  if [[ $shouldBuild = 'y' ]]; then
    make
    echo "Done building."
  else
    echo "Cannot continue without restored_external binary."
    exit
  fi
fi

if [[ -f hacked_ramdisk.dmg ]]; then
  read -p "Found previous hacked ramdisk in working directory. Would you like to delete?: " shouldDel
  if [[ $shouldDel = 'y' ]]; then
    echo "Deleting previous ramdisk..."
    rm hacked_ramdisk.dmg
    sleep 0.5
    echo "Deleted. Continuing..."
  else
    echo "Cannot continue with previous ramdisk. Please relocate it if you want to save it."
    exit
  fi
fi

read -p "Drag the input ramdisk here: " inPACRD
xpwntool $inPACRD user_ramdisk.dmg
hdiutil attach user_ramdisk.dmg
sleep 3
echo "Ramdisk mounted."
sleep 0.5
echo "Entering ramdisk..."
# Mainly to prevent accidental ejection of the ramdisk during the process.
# Having it open in a terminal makes it think an application is using it, stopping it from being ejected.
cd /Volumes/ramdisk/usr/local/bin/
echo "Removing original restored_external..."
rm restored_external
echo "Copying other restored_external file..."
cp $rePATH/tools/restored_external restored_external
echo "Done copying. Should already be chmod'ed correctly."
echo "Exiting ramdisk..."
cd $rePATH
echo "Ejecting ramdisk..."
hdiutil detach "/Volumes/ramdisk"
echo "Ramdisk ejected."
echo "Changing ramdisk into an uploadable DMG in img3 file format..."
xpwntool user_ramdisk.dmg hacked_ramdisk.dmg -t $inPACRD
echo "Cleaning up..."
rm user_ramdisk.dmg
sleep 1
echo "Ramdisk with hacked restored_external written as hacked_ramdisk.dmg. It is ready to be written to an iOS device (armv7 of course :P)"
exit
