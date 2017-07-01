# Common Print Dialog

## Requirements
- libpoppler-qt5-dev
- libcups2-dev
- Qt 5.8 or above

## Build
To build the master branch

```
mkdir build; cd build
qmake .. CONFIG += debug
make all
```

To build the backend_integration branch

```
git checkout backend_integration
git submodule init
git submodule update
cd backends/cups/
make gen
make all
sudo ./install.sh
cd ../../
mkdir build; cd build
qmake .. CONFIG += debug
make all
```
