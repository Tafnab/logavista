
<h1 align="center">
  <br>
   <img src="https://github.com/Tafnab/logavista/blob/master/logo.svg" />
  <br>
</h1>
<p align="center">  
<a href="https://gitter.im/Tafnab/community"><img src="https://avatars.githubusercontent.com/u/19742500?s=60&v=4"></a>
 <a href="https://opensource.org/licenses/gpl-2.0"><img src="https://img.shields.io/badge/license-GPL-blue.svg"></a>
</p>

<p align="center">
  <br>
  Logavista System Log Viewer
  <br>
</p>

<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#feedback">Feedback</a> •
  <a href="#known-bugs">Bugs</a> •
  <a href="#build-instructions">Build Instructions</a> •
  <a href="#related">Related</a> •
  <a href="#license">License</a>
</p>
![screenshot](https://github.com/Tafnab/logavista/blob/master/screenshots/Screenshot.png)

## Key Features

* >>> Software is in Beta Testing Currently >>>
* Allows viewing of over 20 log file types
* Can merge log files of different types providing they have a valid timestamp
* Customized specifically for MX Linux (Debian)
* Tabbed viewing (press Ctl-T) to monitor multiple logs
* Live viewing of log files.
* Search the logs using keywords or filter by priority level of 


## How To Use

<p>You can download the .deb binary file or <a href="#build-instructions">build your own</a>.</p>

<p>On MX Linux, just run from the graphical menu System/Logavista option. On other Linux(es), the graphical option won't work because you need to launch with mx-pkexec or gksu. If you have either of those installed, edit the /usr/share/applications/logavista.desktop file to change the launcher.</p>

<p>Oherwise, you can open a terminal and run:</p>
<pre><code>$ sudo /usr/bin/logavista &</code></pre>

<p>Logavista will open with minimal icons on the toolbar and <b>no tabs</b>. <br>The <b>toolbar must be configured</b> by you in order to see more icons. <b>Tabs can be created</b> by pressing Ctl-T.</p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/ScreenshotNoTabsOpen.png" alt="screenshot-no-tabs">
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/ConfigureToolbars.png" alt="">

<p>Logs are found in the <b>Logs</b> menu. <b>HOWEVER</b>, a log modality will not appear there until it has a valid log file to monitor. </p>

<p>Logavista attempts to auto-populate your default log files with choices that make sense. To configure logs and Logavista in general, select the Settings/Configure_Logavista menu. This will open a dialog that allows you to see which log files a particular Log Mode is monitoring. Use the Add and Remove buttons to change your log files. Keep in mind that the software expects the logs to be in a particular format. In fact, the name of the log file is frequently used to adjust the data presented to you. So, make sure they have the typical names. Use the Merge or "Merge All" buttons to add log files to the Merged Logs modality.</p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/ConfigureToolbars.png" alt="">

<p>You can use the search bar across the top to search for particular events, or use the Dropdown Priorities menu to select which alert levels you want to monitor. </p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/PrioritiesDropdown.png" alt="" align="right>

<p>The default priority is INFO. So, removing INFO from the priorities list allows you to see errors and debug messages.</p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/PrioritiesDropdownNoInformative.png" alt="" align="left">

<p>You can configure the Toolbar by using a right click (context menu) on the toolbar, and selecting "Configure Toolbars". Because this is a KDE application, you can also use this menu to control whether the icons display text. DON'T change the icon size to default unless you want it that way permanently.</p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/ConfigureToolbarsDropdown.png" alt="">

<p>The most exciting feature is the MergedLogs. This allows log files of different types to be merged into one. By default, it is populated with the /var/log/syslog. You can use the merge buttons in the configuration dialog to add files to the MergedLogs or just add them directly. A word of warning... not all log lines will show up unless they have a valid timestamp. There's no way to sort them otherwise.</p>
<img src="https://github.com/Tafnab/logavista/blob/master/screenshots/ConfigureMerge.png" alt="">

<p>The status bar at the bottom of the window has a popup listing log histories.</p>

## Feedback

<p><b>Logavista</b> is based on a previous project which requires that new classes be derived to monitor different log file types. As a result, adding new log modalities isn't trivial.</p>

<p>Many of the log file types lack proper timestamps and host/process information. I have created a simple algorithm to add timestamps and parse the different log file types so that they are understandable. I am looking for feedback on how well this is being accomplished.</p>

<p>In particular, I have not had the chance to test against modern Samba, Apache, CUPS, mail transport programs, and Acpid log file types. </p>

<p>I am also looking for different log file types to monitor that aren't currently listed, but are in common use. Please open an Issue feature request if you have some worthy candidate. I would like sample log files, and would prefer difficult ones indicating errors so that I can make sure the error priority classification scheme is working.</p>

## Build Instructions

<p>Make sure your system is set up to build Qt5 and KDE4/5 packages. You will need a C++17-capable compiler. This is a CMake project, so you will need CMake installed. I currently have it configured for gcc, but clang seems to build fine as well.</p>

<p>Download the source code. Change directory to the new directory and run the following commands in order.</p>
<pre><code>
* mkdir build; cd build;
* make -j4 ..
* sudo make install
* sudo /usr/bin/logavista (to test)
</code></pre>

* Depends: 
<code>kio, libc6 (>= 2.14), libgcc1 (>= 1:3.0), libkf5archive5 (>= 4.96.0), libkf5auth5 (>= 4.96.0), libkf5codecs5 (>= 4.96.0), libkf5completion5 (>= 4.97.0), libkf5configcore5 (>= 4.98.0), libkf5configgui5 (>= 4.97.0), libkf5configwidgets5 (>= 4.96.0), libkf5coreaddons5 (>= 4.100.0), libkf5i18n5 (>= 4.97.0), libkf5iconthemes5 (>= 4.96.0), libkf5itemviews5 (>= 4.96.0), libkf5jobwidgets5 (>= 4.96.0), libkf5kiocore5 (>= 4.96.0), libkf5kiowidgets5 (>= 4.96.0), libkf5service-bin, libkf5service5 (>= 4.96.0), libkf5sonnetui5 (>= 4.96.0), libkf5textwidgets5 (>= 4.96.0), libkf5widgetsaddons5 (>= 4.96.0), libkf5xmlgui5 (>= 4.98.0), libqt5concurrent5 (>= 5.0.2), libqt5core5a (>= 5.11.0~rc1), libqt5dbus5 (>= 5.0.2), libqt5gui5 (>= 5.7.0), libqt5network5 (>= 5.0.2), libqt5printsupport5 (>= 5.0.2), libqt5widgets5 (>= 5.11.0~rc1), libqt5xml5 (>= 5.0.2), libstdc++6 (>= 6)</code>

<p>If you want to see the changes to the code, just clone KSystemlog and Logavista and run a diff on the directories. I suggest using <a href="https://meldmerge.org/">Meld</a>.</p>


## Bugs

* The Log menu occasionally flake out. Ksystemlog did that too. I haven't quite figured it out yet.
* There are leftover links to the original project. These need to be removed.
* Adding files to a Log Modality that currently has no files or invalid files doesn't activate the log until restart. This is possibly my fault. It happens most with MergedLogs. It's on my list to fix.

## Related

* This software was forked from KDE's <a href="https://github.com/KDE/ksystemlog">Ksystemlog 18.08 </a>.

## License

[GPL](LICENSE) - J.D. Nicholson - 2021

