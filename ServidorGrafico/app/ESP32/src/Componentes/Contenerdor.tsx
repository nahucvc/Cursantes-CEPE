import { useState, useEffect } from "react";
import FormularioWIFI from "./FormularioWifi";
import FormularioRemoto from "./FormularioRemoto";

interface parametros {
    children?: React.ReactNode;

}

export default function Contenedor(data: parametros) {
    const [contenido, setcontenido] = useState(FormularioWIFI());


    useEffect( ()=>{clipSelec('Wifi-P')},[]);




    function clipSelec (id)
    {
     const etiqueta = document.getElementById(id) as HTMLElement
        if (etiqueta) {
            etiqueta.style.background= '#989898ff'
            etiqueta.style.boxShadow='2px 2px 2px #050505ff' 
        }
    }
    function deSelec (id:string)
    {
        const etiqueta = document.getElementById(id) as HTMLElement
        etiqueta.style.background= '#8e8b8bff'
         etiqueta.style.boxShadow= '0px 0px 0px #0000'
    }

    function clipWifi (e)
    {
        clipSelec('Wifi-P');
        deSelec('Remoto-P')
        setcontenido(FormularioWIFI());
    }
    function clipRemoto (e)
    {
        clipSelec('Remoto-P');
        deSelec('Wifi-P');
        setcontenido(FormularioRemoto());
    }


    return (
        <div className="space Contenedor-1 radio-1 sombra-1" style={{ background: '#e6ffe4ff', display: 'flex', flexDirection: 'column', justifyContent: 'start', overflow: 'hidden' }}>
            <div className="pestaña" style={{ background: '#8e8b8bff', display: "flex" }}>
                <div className="f center p-0" id="Wifi-P" onClick={clipWifi} style={{ width: '50%' }} > <h4 onClick={()=>{}}><strong>⚙️ WIFI</strong> </h4> </div>
                
                <div className="f center p-0" id="Remoto-P" onClick={clipRemoto} style={{ width: '50%' }} > <h4 onClick={()=>{}}><strong>⚙️ Remoto</strong> </h4> </div>
            </div>
              {contenido}
        </div>)
}