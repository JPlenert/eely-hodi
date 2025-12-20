class rgb24{
    red: number;
    green: number;
    blue: number;

    toCSSColor() : string{
        return "#" + (this.red.toString(16)).padStart(2, "0") +
        (this.green.toString(16)).padStart(2, "0") + 
        (this.blue.toString(16)).padStart(2, "0");
    }

    isBlack() : boolean{
        return this.red == 0 && this.green == 0 && this.blue == 0;
    }
};

function decodeValue(ch: string) : number{
    var val : number = ch.charCodeAt(0);
    if (val >= 0x61)
        return ch.charCodeAt(0) - 0x61 + 45;
    else
        return ch.charCodeAt(0) - 0x30;
}

function decompressScreenShot(shot: string) : Array<rgb24>{
    var colorTable : Array<rgb24> = [];
    var picture : Array<rgb24> = [];


    if (shot[0] != '#' || shot[1] != '0'){
        throw new Error('Invalid shot version');
    }

    for (var curShotIdx: number = 2; curShotIdx < shot.length;){
        // Add color?
        if (shot[curShotIdx] == '!') {
            var newColor : rgb24 = new rgb24();
            var val0, val1 : number;

            val0 = decodeValue(shot[curShotIdx + 1]);
            val1 = decodeValue(shot[curShotIdx + 2]);
            newColor.red = val0 << 2;
            newColor.red += (val1 & 0x30) >> 4;
            newColor.green = (val1 & 0x0F) << 4;
            val0 = decodeValue(shot[curShotIdx + 3]);
            val1 = decodeValue(shot[curShotIdx + 4]);
            newColor.green += (val0 & 0x3C) >> 2;
            newColor.blue = (val0 & 0x03) << 6;
            newColor.blue += val1;

            colorTable.push(newColor);
            curShotIdx += 5;
        }
        else
        {
            let val0 : number = decodeValue(shot[curShotIdx++]);

            // Single pixel
            if (val0 < 32)
            {
                var colorIdx : number = val0;
                picture.push(colorTable[colorIdx]);
            }
            // Multi pixel
            else
            {
                var pixelCount : number = val0 + 2 - 32;
                var colorIdx : number = decodeValue(shot[curShotIdx++]);

                for (var pixelIdx: number = 0; pixelIdx < pixelCount; pixelIdx++) {
                    picture.push(colorTable[colorIdx]);   
                }
            }            
        }
    }

    return picture;
}

function drawToScreen(picture: Array<rgb24>, canv : HTMLCanvasElement, ctx : CanvasRenderingContext2D) : void {
    let fieldSize : number =  Math.floor(canv.width / 64);
    let ledSize : number =  Math.floor(fieldSize / 2);
    let ledSpace : number = Math.floor(fieldSize / 4);
    
    for (var row = 0; row < 32; row ++){
        for (var col = 0; col < 64; col ++){

            // todo: check last color
            if (picture[row*64 + col].isBlack()){
                ctx.fillStyle = "#101010";
            }
            else
            {
                ctx.fillStyle = picture[row*64 + col].toCSSColor();
            }

            ctx.beginPath();
            ctx.arc(2+ col * fieldSize + ledSpace, 2+ row * fieldSize + ledSpace, ledSize / 2, 0, 360);
            ctx.fill();
        

        }
    }
}


window.onload = async () => {
    var c : HTMLCanvasElement = <HTMLCanvasElement>document.getElementById("myCanvas");
    c.height = Math.floor(c.height / 32) * 32;
    c.width = c.height * 2;
    var ctx : CanvasRenderingContext2D = c.getContext("2d");
    ctx.filter = "brightness(150%)";


    let but = <HTMLButtonElement>document.getElementById("calcShot");
    let shotData = <HTMLInputElement>document.getElementById("shotData");

    shotData.value = "#0!0000|0|0|0l0!003sQ1|0f0P1|0f0P1|0U0Q1Q0Q1R0P1P0P10P1V0Q1P0P10P1i0P10P10P10P1Q0P1P0P10P1U0P10P10P10P1i0S10S1Q0P1P0P10P1U0S10P10P1i0P1R0P1T0P1P0P10P1Q0Q10P1R0P10P1j0R1P0R1R0P1P0R1Q0Q1P0R1P0P101|0P0P1y0!002?2Z02Q02Q0Q1V02V0P2g02Z02c0202T02P02f0Q2Q0P2Q0Q2P0P2V0202P0202T02P02f02P0202P0202P02Q02V0202P0202U0Q2f02P0202P0202P02Q02V0202P0202P0P2S02f02P02P0P2Q0Q2P0Q2V02R02Q0P2Q0P2|0|0|0|0|0|0{0!07p03U03Q03|0Z0P3T0Q3|0U0P3P03030P3Q03|0W03P0303P03Q03|0V0Q303030Q3Q03|0|0|0|0|0|0|0|0|0q0";

    but.onclick = () => {
        var picture = decompressScreenShot(shotData.value);
        ctx.fillStyle = "black";
        ctx.fillRect(0, 0, c.width, c.height);
        drawToScreen(picture, c, ctx);    
    };

    but.onclick.call(null);



    
}