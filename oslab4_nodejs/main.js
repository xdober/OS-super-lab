const electron = require('electron');
const {app} = electron;
const {BrowserWindow} = electron;

let mainWindow;
function creatWindow() {
    mainWindow = new BrowserWindow({width: 1100,
        height: 640,
        minHeight: 640,
        minWidth: 1100,
        resizable: true});
    mainWindow.loadURL(`file://${__dirname}/index.html`);
    mainWindow.webContents.openDevTools();
    mainWindow.setMenu(null);
    mainWindow.on('closed',() => {
        mainWindow = null;
    });
}
app.on('ready', creatWindow);
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});
app.on('activate', () => {
    if (mainWindow === null) {
        creatWindow();
    }
});
