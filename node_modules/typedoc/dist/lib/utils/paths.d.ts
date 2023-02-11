import { Minimatch } from "minimatch";
/**
 * Convert array of glob patterns to array of minimatch instances.
 *
 * Handle a few Windows-Unix path gotchas.
 */
export declare function createMinimatch(patterns: string[]): Minimatch[];
export declare function matchesAny(patterns: readonly Minimatch[], path: string): boolean;
export declare function nicePath(absPath: string): string;
