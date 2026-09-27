#!/bin/bash
set -e

rm -rf build AppDir *.AppImage linuxdeploy appimagetool

mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
cd ..

mkdir -p AppDir/usr/bin
cp build/cc AppDir/usr/bin/
chmod +x AppDir/usr/bin/cc

mkdir -p AppDir/usr/styles AppDir/usr/res
cp -r styles/* AppDir/usr/styles/
cp -r res/* AppDir/usr/res/

cat > AppDir/AppRun << 'EOF'
#!/bin/bash
cd "$(dirname "$0")/usr/bin"
exec ./cc "$@"
EOF
chmod +x AppDir/AppRun

cat > AppDir/cc.desktop << 'EOF'
[Desktop Entry]
Type=Application
Name=Converter
Exec=cc
Icon=cc
Categories=Utility;
Terminal=false
EOF

if [ -f res/converter.png ]; then
    convert res/converter.png -resize 256x256\! AppDir/cc.png
elif [ -f res/icon.png ]; then
    convert res/icon.png -resize 256x256\! AppDir/cc.png
else
    convert -size 256x256 xc:blue AppDir/cc.png
fi

if [ ! -f linuxdeploy ]; then
    wget -c "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage" -O linuxdeploy
    chmod +x linuxdeploy
fi

./linuxdeploy --appdir AppDir \
    --plugin qt \
    --executable AppDir/usr/bin/cc \
    --desktop-file AppDir/cc.desktop \
    --icon-file AppDir/cc.png

if [ ! -f appimagetool ]; then
    wget -c "https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage" -O appimagetool
    chmod +x appimagetool
fi

./appimagetool AppDir Converter.AppImage

echo "Готово: $(ls -lh Converter.AppImage)"