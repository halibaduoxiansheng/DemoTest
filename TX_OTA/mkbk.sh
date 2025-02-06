#!/bin/sh

usage(){
	echo "Usage: filename"
	exit	
}

if [ $# -lt 1 ]; then
	usage
fi

oriFirm=$1
newFirm="$1".firm
echo "Make BK Firmware...."
if [ ! -f $oriFirm ]; then
	echo "Orignal Firmware $oriFirm Not Exist"
	exit
fi
md5str=`md5sum $oriFirm | cut -d ' ' -f1`
echo "Orignal Firmware $oriFirm md5:$md5str"
./bk_firmware $oriFirm $md5str
echo "New Firmware Name:$newFirm"
if [ ! -f $newFirm ]; then
	echo Make New Firmware Failed
	exit 
fi
exit
#echo "Add U-boot..."


mkdir $version
finFirm="./$version/fw-$vendor-$product-$version"
if [ -f $finFirm ]; then
	rm  $finFirm
fi 
cp $newFirm $finFirm
cp $oriFirm ./$version/
echo "vendor=$vendor" > ./$version/baseinfo
echo "product=$product" >> ./$version/baseinfo

rm $newFirm

echo "Make Firmware Successful..."
