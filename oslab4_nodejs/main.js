const electron = require('electron');
const {app} = electron;
const {BrowserWindow} = electron;

let mainWindow;
function creatWindow() {
    mainWindow = new BrowserWindow({width: 1100,
        height: 600});
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

const ipcMain = require('electron').ipcMain;
ipcMain.on('asynchronous-message', function(event, arg) {
    console.log(arg);
    event.sender.send('asynchronous-reply', 'pong');
});
ipcMain.on('synchronous-message', function(event, arg) {
    console.log(arg);
    event.returnValue = 'pong2';
});
