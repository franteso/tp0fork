#include "client.h"

int main(void)
{
    /*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
    int conexion;
    char* ip;
    char* puerto;
    char* valor;

    t_log* logger;
    t_config* config;

    /* ---------------- LOGGING ---------------- */
    logger = iniciar_logger();
    log_info(logger, "Soy un Log");

    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
    config = iniciar_config();
    ip = config_get_string_value(config, "IP");
    puerto = config_get_string_value(config, "PUERTO");
    valor = config_get_string_value(config, "CLAVE");
    log_info(logger, "Config cargado. IP: %s - Puerto: %s", ip, puerto);

    /* ---------------- LEER DE CONSOLA ---------------- */
    leer_consola(logger);

    /*---------------------------------------------------CONEXION------------------------------------------------------------*/
    conexion = crear_conexion(ip, puerto);

    enviar_mensaje(valor, conexion);

    paquete(conexion);

    terminar_programa(conexion, logger, config);

    /*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
    return 0;
}

t_log* iniciar_logger(void)
{
    t_log* nuevo_logger = log_create("tp0.log", "CLIENTE", 1, LOG_LEVEL_INFO);
    return nuevo_logger;
}

t_config* iniciar_config(void)
{
    t_config* nuevo_config = config_create("cliente.config");
    return nuevo_config;
}

void leer_consola(t_log* logger)
{
    char* leido;
    leido = readline("> ");

    while (leido != NULL && strcmp(leido, "") != 0) {
        log_info(logger, "Consola: %s", leido);
        free(leido);
        leido = readline("> ");
    }
    free(leido);
}

void paquete(int conexion)
{
    char* leido;
    t_paquete* nuevo_paquete = crear_paquete();

    leido = readline("> ");

    while (leido != NULL && strcmp(leido, "") != 0) {
        agregar_a_paquete(nuevo_paquete, leido, strlen(leido) + 1);
        free(leido);
        leido = readline("> ");
    }
    free(leido);

    enviar_paquete(nuevo_paquete, conexion);
    eliminar_paquete(nuevo_paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
    log_destroy(logger);
    config_destroy(config);
    liberar_conexion(conexion);
}