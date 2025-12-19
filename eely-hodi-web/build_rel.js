const res = require('esbuild');
const fs = require('fs');
const { exec } = require( 'child_process' );

console.log( `building release with esbuild` );

res.buildSync({
    entryPoints: ['./src/app.tsx'],
    outfile: 'dist/index.js',
    bundle: true,
    minify: true,
    sourcemap: false,
    treeShaking: true,
    keepNames: false,
  })

console.log( `creating minified single file for ESP` );
exec("dotnet ./modules/eely-base-web/_contrib/HtmlSingler.dll index.html index.min.html all");
