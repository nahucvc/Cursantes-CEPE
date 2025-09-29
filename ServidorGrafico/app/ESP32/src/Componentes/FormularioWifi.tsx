

export default function FormularioWIFI ()
{
    return(
        <div className="space" style={{width:'100%', height:'100%' , display:"flex", flexDirection:'column' }}> 
        
        <form style={{width:'100%', height:'100%' , display:"flex", flexDirection:'column', justifyContent:'start' }}>
        <label className="etiquetas sombra-tex-0" htmlFor="SSID"> Nombre de la Red a Conectarse </label>
        <input className="entradas" type="text" name="SSID" id="SSID" placeholder="SSID" />
        <label className="etiquetas sombra-tex-0" htmlFor="password"> Contraseña</label>
        <input className="entradas" type="text" name="SSID" id="password" placeholder="Password" />
        <button className="boton"> Enviar </button>

        </form>
            
        </div>

     )
}