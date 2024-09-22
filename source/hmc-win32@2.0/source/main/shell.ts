import main = require("./index");
import util = require("./util");
const {ref} = util;

const HMC2 = main.native;

class Startup {
    #Startup: null | main.HMC2.HMC_SHELL_STARTUP_CLASS = null;

    #initialize() {
        if (!this.#Startup&&HMC2.native.HMC_SHELL_STARTUP_CLASS) {
            this.#Startup = HMC2.native.HMC_SHELL_STARTUP_CLASS();
        }
    }
    
    #root:"HKEY_LOCAL_MACHINE" = "HKEY_LOCAL_MACHINE";
    #pathRun ="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    #pathRunOnce = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
    constructor() { }

    has(keyName: string) {
        this.#initialize();
        return this.#Startup?.has(ref.string(keyName)) || false;
    }

    hasOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.hasOnce(ref.string(keyName)) || false;
    }


    remove(keyName: string) {
        this.#initialize();
        return this.#Startup?.remove(ref.string(keyName)) || false;
    }


    removeOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.removeOnce(ref.string(keyName)) || false;
    }

    set(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.set(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    setOnce(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    enum() {
        const obj:{[key:string]:string} = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRun);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRun, at);
        // }
        return obj;
    }
    
    enumOnce() {
        const obj:{[key:string]:string} = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRunOnce);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRunOnce, at);
        // }
        return obj;
    }

    keys(){
        return[];
        // return native.enumRegistrKey(this.#root,this.#pathRun);
    }
    
    keysOnce(){
        return [];
        // return native.enumRegistrKey(this.#root,this.#pathRunOnce);
    }
}

export const startup = new Startup();
