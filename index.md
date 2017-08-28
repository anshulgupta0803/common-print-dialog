# Common Print Dialog
[Common Print Dialog](https://summerofcode.withgoogle.com/projects/#4923803856535552) is part of Google Summer of Code 2017 under [The Linux Foundation](https://www.linuxfoundation.org/). The project plan can be found [here](https://docs.google.com/document/d/1OhPCdYRYftfQkuKljjjCNdxcnsm-6TlluyGeQL35tdM/edit).

This aims of this project was to create a unified solution for printing in desktop environments. A well designed print dialog will help the users to find the right printers as well as the right printing configurations for documents. And this will happen in a way which is consistent with every platform. The front-end of the print dialog is ergonomic and written in Qt. The back-end has the functionality for printing with CUPS, IPP or Google Cloud Print.

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
