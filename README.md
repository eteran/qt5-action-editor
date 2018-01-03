# qt4-action-editor
A port of qq14-actioneditor from Qt Quarterly to Qt4

There was an [interesting issue of Qt Quarterly](https://doc.qt.io/archives/qq/qq14-actioneditor.html) way back when which demonstrated 
how to make an application wide shortcut editor. Unfortunately the code was 
Qt3 only. So, I decided to port it to Qt4 in case someone might find it useful.

In addition to straight code porting, I also updated some other things such as:

1. Using UI files to describe the GUI. Since the point of this example is not really teaching anything about the UI, this helps focus on the code that is relevent.
2. Using cmake as the build system over qmake.
