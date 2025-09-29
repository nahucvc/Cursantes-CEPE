import type { ReactNode } from "react"
import './estilo.css'
interface datos
{
    children?: ReactNode;
}

export default function Cuerpo({children}:datos) 
{
    return ( <div className="cuerpo"> 
     {children} 
    </div> )
}