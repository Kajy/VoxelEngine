
//% weight=80 icon="\uf005" color=#073A5A
namespace basic {
    ////////////////
    //  EVENTS
    ////////////////
   
    /**
     * When player put a command on chat
     * @param body Function when player put a command
     */
    //% blockId=onStart block="Au démarrage" blockGap=8
    //% weight=100
    //% parts="onStart" shim=::webSocketManager::log
    //% group="Boucle de jeu"
    export function onStart(functions: () => void): void{
        webSocketManager.initialiseEvent();
        let event = {};
        functions();
        webSocketManager.sendEvent("onStart", event);
    }; 


    /**
     * When player put a command on chat
     * @param body Function when player put a command
     */
    //% blockId=onChatCommand block="Lorsque lance la commande %cmd" blockGap=8
    //% weight=100
    //% parts="onChatCommand" shim=::webSocketManager::log
    //% group="Évènements liés au chat"
    export function onCommand(cmd:string, functions: () => void): void{
        webSocketManager.initialiseEvent();
        let event = {};
        if (cmd.length > 0)
            event = {
                "parameters":
                [{ type: "string", name: "command", value:cmd }]
            };
        functions();
        webSocketManager.sendEvent("command", event);
    };

    /**
     * When player put something on chat
     * @param body Function when player put something on chat
     */
    //% blockId=onPlayerChat block="Lorsqu'il y a un message dans le chat" blockGap=8
    //% parts="onPlayerChat" shim=::webSocketManager::log
    //% weight=100
    //% group="Évènements liés au chat"
    export function onPlayerChat(functions: () => void): void{
        webSocketManager.initialiseEvent();
        let event = {};
            event = {
                "parameters":
                [{ type: "string", name: "message" }]
            };
        functions();
        webSocketManager.sendEvent("playerChat", event);
    };

    /**
     * When player put something on chat
     * @param body Function when player put something on chat
     */
    //% blockId=onPlayerChatMsg block="Lorsque l'on écrit %msg dans le chat" blockGap=8
    //% parts="onPlayerChatMsg" shim=::webSocketManager::log
    //% weight=100
    //% group="Évènements liés au chat"
    export function onPlayerChatMsg(msg:string, functions: () => void): void{
        webSocketManager.initialiseEvent();
        let event = {};
        if (msg.length > 0)
            event = {
                "parameters":
                [{ type: "string", name: "message", value:msg }]
            };
        functions();
        webSocketManager.sendEvent("playerChat", event);
    };

    
    ////////////////
    //  FUNCTIONS
    ////////////////
    /**
     * Player write in chat
     */
    //%  blockId=say block="Écrire %msg dans le chat" shim=::webSocketManager::sendFunction
    //% weight=90
    //% group="Fonctions de chat"
    export function say(msg:string) {
        let component = {
        "parameters":
        [
            {
                type: "string",
                value: msg,
                name: "message1"
            }
        ]
    };
    webSocketManager.formatFunction("say", "action", "function", component);
}
 
    /**
     * Player write a title
     */
    //%  blockId=title block="Afficher %msg pendant %duration" shim=::webSocketManager::sendFunction
    //% weight=90
    //% group="Fonctions d'informations"
    export function sendTitle(msg:string, duration: number) {
        let component = {
        "parameters":
        [
            {
                type: "string",
                value: msg,
                name: "message"
            },
            {
                type: "decimal",
                value: duration,
                name: "duration"
            }
        ]
    };
    webSocketManager.formatFunction("title", "action", "function", component);
}
}