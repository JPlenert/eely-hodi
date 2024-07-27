// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

class GasValues extends Control{

    protected getButton : HTMLButtonElement;

    protected getInnerHtml() : string {
        return `
            <div class="row row-header">
                <div class="col row-header-content">Ten minute values</div>
            </div>
            <div class="row">              
                <div class="col pad-lr-1"><div class="form-control text-center" id="${this.id}ten">Values</div></div>
            </div>

            <div class="row row-header">
                <div class="col row-header-content">Hour values</div>
            </div>
            <div class="row">              
                <div class="col pad-lr-1"><div class="form-control text-center" id="${this.id}hour">Values</div></div>
            </div>

            <div class="row">
                <div class="col"><button type="submit" class="btn btn-primary" id="${this.id}get">get</button></div>
            </div>
            `;
    }

    protected initControlLate(): void {

        this.getButton = <HTMLButtonElement>this.htmlElement.querySelector(`#${this.id}get`);
        this.getButton.onclick = async ()  => { 
            // let cValues = await globalHoDi.comGas.gasMeterValues_get();            
            // (window.document.getElementById(`${this.id}ten`) as HTMLDivElement).innerText = cValues.TenMin.toString();
            // (window.document.getElementById(`${this.id}hour`) as HTMLDivElement).innerText = cValues.Hour.toString();
            };
    }
}

