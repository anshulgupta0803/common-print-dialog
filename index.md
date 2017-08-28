# Common Print Dialog
[Common Print Dialog](https://summerofcode.withgoogle.com/projects/#4923803856535552) is part of Google Summer of Code 2017 under [The Linux Foundation](https://www.linuxfoundation.org/). The project plan can be found [here](https://docs.google.com/document/d/1OhPCdYRYftfQkuKljjjCNdxcnsm-6TlluyGeQL35tdM/edit).

The aim of this project is to create a unified solution for printing in desktop environments. A well designed print dialog will help the users to find the right printers as well as the right printing configurations for documents. And this will happen in a way which is consistent with every platform. The front-end of the print dialog is ergonomic and written in Qt. The back-end has the functionality for printing with CUPS, IPP or Google Cloud Print.

# Mentors
__Dongxu Li__
- Contact: dongxuli2011 [at] gmail [dot] com
- Github: https://github.com/dxli

__Aveek Basu__: Linux Foundation Org Admin (Lexmark)
- Contact: basu [dot] aveek [at] gmail [dot] com

__Till Kamppeter__: Linux Foundation Org Admin (Canonical)
- Contact: till [dot] kamppeter [at] gmail [dot] com
- Github: https://github.com/tillkamppeter

# Project Structure
The project has 2 main modules. The QCPDialog and Helper.

## QCPDialog Library
QCPDialog is a Qt library which can be used in replacement of the current [QPrintDialog](https://doc.qt.io/qt-5/qprintdialog.html). QCPDialog follows the exact same structure as that of QPrintDialog so the only change that the developer has to do is include the appropriate header file (`QCPDialog.h`) and the library (`-lQCPDialog`) and replace `QPrintDialog(...)` with `QCPDialog(...)` without changing the arguments to the function.

## Helper Program
The helper program is the one which issues the print command to the printer. The user is agnostic to this program as it is triggered automatically in the background and as soon as the data to print is available, it sends the print command and exits quietly.

# Dependencies
This project uses [Frontend and Backend Libraries for Common Print Dialog](https://github.com/NilanjanaLodh/OpenPrinting_CPD_Libraries) to interact with the backends.

The dialog is totally unaware of what backends are present in the system. The Backend library automatically detects the backends installed in the system for use.

Here are a couple of backends which can be used for this dialog:
- [CUPS Backend](https://github.com/NilanjanaLodh/OpenPrinting_CUPS_Backend)
- [Google Cloud Print Backend](https://github.com/dracarys09/gcp-backend)

Whenever a new backend (adhering to the guidelines of the backend library) is installed in the system, it will automatically appear in the print dialog.

Other dependencies are:
- qt5-qmake
- qtdeclarative5-dev
- qml-module-qtquick-controls
- qml-module-qtquick-controls2
- qml-module-qtquick-templates2
- qml-module-qtquick-dialogs

On Ubuntu/Debian based systems, run this command:
```
sudo apt -y install qt5-qmake qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-controls2 qml-module-qtquick-templates2 qml-module-qtquick-dialogs
```
# QCPDialog Library
## UI Design
The dialog design takes cues from Gnome's [Tentative Design for Print Dialog](https://wiki.gnome.org/Design/OS/Printing#Tentative_Design) but is much more feature richness than what's proposed in the tentative design.

The UI is designed using [Qt QML](https://doc.qt.io/qt-5/qtqml-index.html) using Material Design and the individual modules can be found in `./qcpdialog/*.qml` files. These modules and the QPrintPreviewWidget are put together in `./qcpdialog/QCPDialog.cpp`.

```
masterLayout
|-tabs
|-root -- preview
|-controls
```

`root` contains various layouts (General, Page Setup, Options, Jobs, Advanced) which switches when a tab is clicked on `tabs`.

`preview` was originally intended to show the live print preview but unfortunately due to the limitations in the way printing works in Qt, the data which the user wants to print is available after the print dialog exists. So for now, `preview` shows a sample but the changes are reflected on the actual print job.

`controls` shows buttons for _Print_, _Cancel_, _Previous_<sup>[1](#footnote1)</sup>, _Zoom Slider_, _Next_<sup>[1](#1)</sup>.

<a name="#footnote1">1</a> - These buttons would work if the preview displayed the actual multi-page document to print.

## Code Interaction with UI
`QCPDialog.{cpp/h}` handles almost all the SIGNALS and SLOTS from/to the UI and is responsible for making the content dynamic.

`components.{cpp/h}` creates [QQuickWidgets](https://doc.qt.io/qt-5/qquickwidget.html) from various qml files and these components are used in `QCPDialog.cpp`.

# Helper Program
This program is responsible for issuing print command to the printer which user has selected in the dialog along the settings. It is automatically invoked by the dialog and then it waits in the background for the print data to be available. As soon as the data is available, it sends the print command and exits.

# Installing the library
Either do a `git clone https://github.com/anshulgupta0803/common-print-dialog.git` or download [zip](https://github.com/anshulgupta0803/common-print-dialog/zipball/master) or [tarball](https://github.com/anshulgupta0803/common-print-dialog/tarball/master)

Then do the following
```
mkdir build
cd build
qmake ..
make
sudo make install
```
# Using the library
The library is present in `/usr/lib/libQCPDialog.1.0.0` and can be used in the application with `-lCPDialog` and the corresponding header file is `/usr/include/common-print-dialog/QCPDialog.h` and can be added to the _INCLUDE_PATH_ with `-I/usr/include/common-print-dialog`.

A sample Hello World application which uses this library can be found [here](https://github.com/anshulgupta0803/printTest)
