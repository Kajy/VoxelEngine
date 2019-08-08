
//% weight=70 icon="\uf1b3" color=#6B8E23
namespace blocs {
    ////////////////
    //  EVENTS
    ////////////////


    /**
    * When player break a bloc on world
    * @param body Function when player break a bloc on world
    */
    //% blockId=onBlockBreak block="Lorsque l'on détruit un bloc" blockGap=8
    //% parts="onBlockBreak"
    //% group="Evenements liés à la destruction des blocs"
    export function onBlockBreak(functions: () => void): void {
        webSocketManager.initialiseEvent();
        let event = {};
        functions();
        webSocketManager.sendEvent("blockBreak", event);
    };

    /**
     * When player break a bloc of a specific type on world
     * @param body Function when player break a bloc of a specific type on world
     */
    //% blockId=onBlockBreakOfType block="Lorsque l'on détruit un bloc de type $materials" blockGap=8
    //% parts="onBlockBreakOfType" shim=::webSocketManager::log
    //% group="Evenements liés à la destruction des blocs"
    export function onBlockBreakWithType(materials: MaterialType, functions: () => void): void {
        webSocketManager.initialiseEvent();
        let event = {};
        let materialType = "";

        switch (materials) {
            case (0):
                materialType = "essentials:stone";
                break;
            case (1):
                materialType = "essentials:grass";
                break;
            case (2):
                materialType = "essentials:dirt";
                break;
            case (3):
                materialType = "essentials:leaves";
                break;
            case (4):
                materialType = "essentials:wood";
                break;
            case (5):
                materialType = "pxt:cross";
                break;
            case (6):
                materialType = "pxt:circle";
                break;
            default:
                materialType = "essantials:stone"
        }

        if (materialType.length > 0)
            event = {
                "parameters":
                    [{ type: "string", name: "material", value: materialType },]
            };
        functions();
        webSocketManager.sendEvent("blockBreak", event);
    };
    `
`
    /**
    * When player place a bloc on world
    * 
    * @param body Function when player place a bloc on world
    */
    //% blockId=onBlockPlace block="Lorsque l'on place un bloc" blockGap=8
    //% parts="onBlockPlace"
    //% group="Evenements liés au placement des blocs"
    export function onBlockPlace(functions: () => void): void {
        webSocketManager.initialiseEvent();
        let event = {};
        functions();
        webSocketManager.sendEvent("blockPlace", event);
    };

    /**
     * When player place a bloc of a specific type on world
     * @param body Function when player place a bloc of a specific type on world
     */
    //% blockId=onBlockPlaceOfType block="Lorsque l'on place un bloc de type $materials" blockGap=8
    //% parts="onBlockPlaceOfType" shim=::webSocketManager::log
    //% group="Evenements liés au placement des blocs"
    export function onBlockPlaceWithType(materials: MaterialType, functions: () => void): void {
        webSocketManager.initialiseEvent();
        let event = {};
        let materialType = "";
        
        switch (materials) {
            case (0):
                materialType = "essentials:stone";
                break;
            case (1):
                materialType = "essentials:grass";
                break;
            case (2):
                materialType = "essentials:dirt";
                break;
            case (3):
                materialType = "essentials:leaves";
                break;
            case (4):
                materialType = "essentials:wood";
                break;
            case (5):
                materialType = "pxt:cross";
                break;
            case (6):
                materialType = "pxt:circle";
                break;
            default:
                materialType = "essantials:stone"
        }

        if (materialType.length > 0)
            event = {
                "parameters":
                    [{ type: "string", name: "material", value: materialType },]
            };
        functions();
        webSocketManager.sendEvent("blockPlace", event);
    };


    ////////////////
    //  VARIABLES
    ////////////////
    /**
   * This is a reporter block that returns a number
   */
    //% block="X"
    //% group="Variables liées au bloc de l'évènement"
    export function blockX(): number {
        return -999;
    }

    /**
* This is a reporter block that returns a number
*/
    //% block="Y"
    //% group="Variables liées au bloc de l'évènement"
    export function blockY(): number {
        return -998;
    }

    /**
* This is a reporter block that returns a number
*/
    //% block="Z"
    //% group="Variables liées au bloc de l'évènement"
    export function blockZ(): number {
        return -997;
    }

    ////////////////
    //  BOOLEAN FUNCTIONS
    ////////////////
    /**
     * Check if the cross is same type of blocks
     * @param body Function when player put a command
     */
    //% blockId=checkCross block="Test croix en %x %y %z de type %mat de longueur %length" blockGap=8
    //% inlineInputMode=inline
    //% parts="checkCross" shim=::webSocketManager::log
    //% group="Fonctions de verification"
    export function checkCross(x: number, y: number, z: number, materials: MaterialType, length: number): boolean {
        webSocketManager.initialiseEvent();
        let materialType = "";

        switch (materials) {
            case (0):
                materialType = "essentials:stone";
                break;
            case (1):
                materialType = "essentials:grass";
                break;
            case (2):
                materialType = "essentials:dirt";
                break;
            case (3):
                materialType = "essentials:leaves";
                break;
            case (4):
                materialType = "essentials:wood";
                break;
            case (5):
                materialType = "pxt:cross";
                break;
            case (6):
                materialType = "pxt:circle";
                break;
            default:
                materialType = "essantials:stone"
        }

        let component =
        {
            "parameters":
                [
                    {
                        type: "variable",
                        value: (x === -999 ? "block_x" : x),
                        name: "x"
                    },
                    {
                        type: "variable",
                        value: (y === -998 ? "block_y" : y),
                        name: "y"
                    },
                    {
                        type: "variable",
                        value: (z === -997 ? "block_z" : z),
                        name: "z"
                    },
                    {
                        type: "string",
                        name: "material",
                        value: materialType
                    },
                    {
                        type: "integer",
                        name: "length",
                        value: length
                    },
                ],
        };
        webSocketManager.formatCondition("check", "function", "checkCross", component);
        return true;
    };

    /**
 * Check if the diagonal is same type of blocks
 * @param body Function when player put a command
 */
    //% blockId=checkDiagonal block="Test diagonale en %x %y %z de type %mat de longueur %length" blockGap=8
    //% inlineInputMode=inline
    //% parts="checkDiagonal" shim=::webSocketManager::log
    //% group="Fonctions de verification"
    export function checkDiagonal(x: number, y: number, z: number, materials: MaterialType, length: number): boolean {
        webSocketManager.initialiseEvent();

        let materialType = "";

        switch (materials) {
            case (0):
                materialType = "essentials:stone";
                break;
            case (1):
                materialType = "essentials:grass";
                break;
            case (2):
                materialType = "essentials:dirt";
                break;
            case (3):
                materialType = "essentials:leaves";
                break;
            case (4):
                materialType = "essentials:wood";
                break;
            case (5):
                materialType = "pxt:cross";
                break;
            case (6):
                materialType = "pxt:circle";
                break;
            default:
                materialType = "essantials:stone"
        }

        let component =
        {
            "parameters":
                [
                    {
                        type: "variable",
                        value: (x === -999 ? "block_x" : x),
                        name: "x"
                    },
                    {
                        type: "variable",
                        value: (y === -998 ? "block_y" : y),
                        name: "y"
                    },
                    {
                        type: "variable",
                        value: (z === -997 ? "block_z" : z),
                        name: "z"
                    },
                    {
                        type: "string",
                        name: "material",
                        value: materialType
                    },
                    {
                        type: "integer",
                        name: "length",
                        value: length
                    },
                ],
        };
        webSocketManager.formatCondition("check", "function", "checkDiagonal", component);
        return true;
    };

    ////////////////
    //  FUNCTIONS
    ////////////////
    /**
     * Draw a cube of type : %material with a radius %radius in position %x %y %z
     */
    //%  blockId=drawCube block="Poser un cube de %material avec un rayon de %radius aux positions %x %y %z" shim=::webSocketManager::sendFunction
    //% inlineInputMode=inline
    //% group="Fonctions liés aux blocs"
    export function drawCube(materials: MaterialType, radius: number, x: number, y: number, z: number) {
        let materialType = "";

        switch (materials) {
            case (0):
                materialType = "essentials:stone";
                break;
            case (1):
                materialType = "essentials:grass";
                break;
            case (2):
                materialType = "essentials:dirt";
                break;
            case (3):
                materialType = "essentials:leaves";
                break;
            case (4):
                materialType = "essentials:wood";
                break;
            case (5):
                materialType = "pxt:cross";
                break;
                case (6):
                materialType = "pxt:circle";
                break;
                case (7):
                materialType = "air";
                break;
            default:
                materialType = "essantials:stone"
        }

        let component = {
            "parameters":
                [
                    {
                        type: "string",
                        value: materialType,
                        name: "material"
                    },
                    {
                        type: "integer",
                        value: radius,
                        name: "radius"
                    },
                    {
                        type: "integer",
                        value: x,
                        name: "x"
                    },
                    {
                        type: "integer",
                        value: y,
                        name: "y"
                    },
                    {
                        type: "integer",
                        value: z,
                        name: "z"
                    },
                ]
        };
        webSocketManager.formatFunction("drawCube", "action", "function", component);
    }
}