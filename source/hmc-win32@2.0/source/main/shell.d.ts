declare class StartupConstructor {
    #private;
    constructor();
    has(keyName: string): boolean;
    hasOnce(keyName: string): boolean;
    remove(keyName: string): boolean;
    removeOnce(keyName: string): boolean;
    set(keyName: string, path: string, cmd?: string): boolean;
    setOnce(keyName: string, path: string, cmd?: string): boolean;
    enum(): {
        [key: string]: string;
    };
    enumOnce(): {
        [key: string]: string;
    };
    keys(): never[];
    keysOnce(): never[];
}
export declare module Shell {
    /**
     * 启动项 管理
     */
    const Startup: StartupConstructor;
    /**
     * 截图为Bmp 文件/Buffer
     */
    const captureBmp2: {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string, handle: number): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    };
    /**
    * 截图为Bmp 文件/Buffer
    */
    const captureBmp2Sync: {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string, handle: number): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;
    };
}
export {};
