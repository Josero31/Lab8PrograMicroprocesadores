#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int NUM_LIBROS = 5;
sem_t semaforoLibros;

void* prestarYDevolver(void* arg) {
    // Intentar prestar un libro
    sem_wait(&semaforoLibros);
    std::cout << "Libro prestado por thread " << pthread_self() << std::endl;

    // Simular el uso del libro
    sleep(1);

    // Devolver el libro
    std::cout << "Libro devuelto por thread " << pthread_self() << std::endl;
    sem_post(&semaforoLibros);

    return nullptr;
}

int main() {
    // Inicializar el semáforo con el número de libros disponibles
    sem_init(&semaforoLibros, 0, NUM_LIBROS);

    // Crear 10 threads
    pthread_t threads[10];
    for (int i = 0; i < 10; ++i) {
        pthread_create(&threads[i], nullptr, prestarYDevolver, nullptr);
    }

    // Esperar a que todos los threads terminen
    for (int i = 0; i < 10; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Destruir el semáforo
    sem_destroy(&semaforoLibros);

    return 0;
}
