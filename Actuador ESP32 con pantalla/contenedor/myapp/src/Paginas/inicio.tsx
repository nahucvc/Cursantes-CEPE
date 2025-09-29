import Titulo from "../componentes/Encabezado/Encabezado"
import { Pesta } from "../componentes/Encabezado/Pestañas"
import Cuerpo from "../componentes/Encabezado/cuerpo"
import DatosWifi from "../componentes/Encabezado/wifi"
export default function Inicio() {
    return (<Titulo>
     <Pesta titulo={["Configuración Wifi", "Configuración MQTT"]}> 
        <Cuerpo>
            <DatosWifi>
                
            </DatosWifi>
        </Cuerpo>
     </Pesta>
     
    </Titulo>)
}