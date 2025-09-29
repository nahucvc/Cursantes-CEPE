

/**
 * Importa los módulos más importantes de React, como:
 * - React: el núcleo de la biblioteca para crear componentes.
 * - useState: para manejar el estado local en componentes funcionales.
 * - useEffect: para manejar efectos secundarios en componentes funcionales.
 * - useContext: para acceder al contexto global de la aplicación.
 * - useRef: para crear referencias a elementos o valores persistentes.
 * - useMemo y useCallback: para optimizar el rendimiento de los componentes.
 */
import type { ReactNode } from "react";
import "./estilo.css";

interface TituloProps {
    children?: ReactNode; // ✔ el nombre estándar que entiende React
}

function Titulo({ children }: TituloProps) {
    return (
        <div className="contenedor">
            <div className="Encabezado">
                <h1>🚀 Actuador CEPE</h1>
            </div>
            {children} {/* ✔ muestra el contenido */}
        </div>
    );
}

export default Titulo;
