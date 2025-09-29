import type { ReactNode } from "react"
import { useState } from "react";
import "./estilo.css"
interface datos {
    children?: ReactNode;
}

export default function DatosWifi({ children }: datos) {
    const [ssid, setSsid] = useState("");
    const [password, setPassword] = useState("");

    function handleSubmit(e: React.FormEvent) {
        e.preventDefault();

        console.log({ ssid, password });
    }
    return (<div id="PesWIFI">
        <label className="margen-20px" htmlFor="SSID">Nombre de la Red WIFI </label>
        <input  type="text" id="SSID" />
        <label className="margen-20px" htmlFor="password"> Contraseña de la Red</label>
        <input  type="text" id="password" min={8} />
        <div className="contendorBotones">
            <button className="margen-20px" id="loadRedbotom"> Guardar Red </button>
            <button className="margen-20px" id="Resetbotom"> Reiniciar Micro</button>
        </div>
        <>{children}</>
    </div>)
}