#ifndef CLASES_H
#define CLASES_H

#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Excepción personalizada
class PreguntaNoEncontrada : public runtime_error {
public:
    PreguntaNoEncontrada();
};

// Clase Pregunta
class Pregunta {
private:
    int id;
    string enunciado;
    string nivelTaxonomico;
    int tiempoEstimado;
    string tipoPregunta;
    int ano;

public:
    Pregunta(int id, string enunciado, string nivelTaxonomico, int tiempoEstimado, string tipoPregunta, int ano);
    void mostrarInfo();
    string getNivelTaxonomico();
    int getTiempoEstimado();
    int getId();
    string getEnunciado();
    string getTipoPregunta();
    int getAno();
    void setEnunciado(string nuevo);
};

// Clase Evaluacion
class Evaluacion {
private:
    vector<Pregunta> preguntas;

public:
    void agregarPregunta(Pregunta p);
    void eliminarPregunta(int id);
    void actualizarPregunta(int id, string nuevoEnunciado);
    void buscarPorNivelTaxonomico(string nivel);
    void mostrarEvaluacion();
    int calcularTiempoTotal();
    void generarEvaluacionPorNivel(string nivel, int cantidad);
};

// Clase SistemaEvaluacion
class SistemaEvaluacion {
private:
    Evaluacion evaluacion;
    vector<string> nivelesValidos;
    bool esNivelValido(string nivel);
    string limpiarInput(string prompt);
    string seleccionarTipoPregunta();

public:
    SistemaEvaluacion();
    void mostrarMenu();
};

#endif
