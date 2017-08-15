# Common Print Dialog

## Requirements
- qt5-qmake
- qtdeclarative5-dev
- qml-module-qtquick-controls
- qml-module-qtquick-controls2
- qml-module-qtquick-templates2
- qml-module-qtquick-dialogs
- libpoppler-qt5-dev
- [Helper libraries and CUPS Backend](https://github.com/NilanjanaLodh/PrintDialog_Backend) and [GCP Backend](https://github.com/dracarys09/gcp-backend)

On Ubuntu, run this command to install all dependencies
```
sudo apt -y install qt5-qmake qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-controls2 qml-module-qtquick-templates2 qml-module-qtquick-dialogs libpoppler-qt5-dev
```

For the helper libraries and CUPS/GCP backends, see their respective README files.

## Build
To build and install the Print Dialog Library

```
mkdir build; cd build
qmake ..
make all
sudo make install
```

## Using the library
https://github.com/anshulgupta0803/printTest

This is a Hello World print application which uses the Print Dialog library.
