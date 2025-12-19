const res = require('esbuild');
const fs = require('fs');
const { exec } = require( 'child_process' );

console.log( `building with esbuild` );

res.buildSync({
    entryPoints: ['./src/app.tsx'],
    outfile: 'dist/index.js',
    bundle: true,
    minify: false,
    sourcemap: true,
    treeShaking: false,
    keepNames: true,
  })
