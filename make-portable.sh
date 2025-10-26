#!/usr/bin/env sh

VERSION=$(printf "%d.%d.%d" $(grep  -E "MAJOR |MINOR |PATCH " CMakeLists.txt | awk -F'(' '{ print $2 }'| awk -F'"' '{ print $2 }'))

echo "Removing old App directory"
rm -Rf amiberry-${VERSION} 
echo "Creating App directory"
# Make directory for App bundle
mkdir -p amiberry-${VERSION} 
# Copy executable into App bundle
cp amiberry amiberry-${VERSION}/ 
# Copy directories into the bundle
cp -R controllers amiberry-${VERSION}/
cp -R data amiberry-${VERSION}/
cp -R plugins amiberry-${VERSION}/
cp -R whdboot amiberry-${VERSION}/
touch amiberry-${VERSION}/amiberry.portable

