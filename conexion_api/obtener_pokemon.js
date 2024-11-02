const axios = require('axios');
const fs = require('fs');

async function obtenerDatosPokemon(id) {
    try {
    const url = `https://pokeapi.co/api/v2/pokemon/${id}/`;
    const respuesta = await axios.get(url);
    const datos = respuesta.data;

    const nombre = datos.name.charAt(0).toUpperCase() + datos.name.slice(1);
    const tipos = datos.types.map(tipo => tipo.type.name.charAt(0).toUpperCase() + tipo.type.name.slice(1)).join('/');
    const hp = datos.stats[0].base_stat;
    const ataque = datos.stats[1].base_stat;
    const defensa = datos.stats[2].base_stat;
    const ataqueEsp = datos.stats[3].base_stat;
    const defensaEsp = datos.stats[4].base_stat;
    const velocidad = datos.stats[5].base_stat;

    // Obtener la descripción
    const urlEspecie = datos.species.url;
    const respuestaEspecie = await axios.get(urlEspecie);
    const datosEspecie = respuestaEspecie.data;
    const entradaDescripcion = datosEspecie.flavor_text_entries.find(entry => entry.language.name === 'en');
    const descripcion = entradaDescripcion ? entradaDescripcion.flavor_text.replace(/\n/g, ' ').replace(/\f/g, ' ') : "Descripción no disponible";

    return {
        id,
        nombre,
        tipos,
        hp,
        ataque,
        defensa,
        ataqueEsp,
        defensaEsp,
        velocidad,
        descripcion
    };
} catch (error) {
    console.error(`Error al obtener los datos del Pokémon con ID ${id}:`, error);
    return null;
    }
}

async function main() {
    const archivo = fs.createWriteStream('pokemon_generacion1.txt', { encoding: 'utf-8' });

for (let i = 1; i <= 151; i++) {
    const datos = await obtenerDatosPokemon(i);
    if (datos) {
        archivo.write(`${datos.id}\n`);
        archivo.write(`${datos.nombre}\n`);
        archivo.write(`${datos.tipos}\n`);
        archivo.write(`${datos.hp}\n`);
        archivo.write(`${datos.ataque}\n`);
        archivo.write(`${datos.defensa}\n`);
        archivo.write(`${datos.ataqueEsp}\n`);
        archivo.write(`${datos.defensaEsp}\n`);
        archivo.write(`${datos.velocidad}\n`);
        archivo.write(`${datos.descripcion}\n`);
        archivo.write('\n'); // Separador entre Pokémon
    }
}

    archivo.end();
    console.log("Archivo 'pokemon_generacion1.txt' creado con éxito.");
}

main();
