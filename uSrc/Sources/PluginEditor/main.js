const { app, BrowserWindow, Menu } = require('electron')
const pxt = require('pxt-core')
const path = require('path')
const { exec } = require('child_process');

let win;

const cliPath = path.join(process.cwd(), "pxt-plugin-editor");

function startServerAndCreateWindow() {
  pxt.mainCli(cliPath, ["serve", "-no-browser"])
  .then(res => createWindow());
  }

function createWindow() {
  win = new BrowserWindow({
    width: 1000,
    height: 1000,
    title: "uCraft - Plugin editor"
  })
  Menu.setApplicationMenu(null)
  win.loadURL(`file://${__dirname}/index.html`)
  //win.webContents.openDevTools();
  win.on('closed', () => {
    win = null
  })
}

app.on('ready', startServerAndCreateWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (win === null) {
    createWindow()
  }
})
