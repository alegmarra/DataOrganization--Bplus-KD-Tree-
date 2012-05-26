#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__

class Serializable {
    public:
        /**
         * @brief deshidratación
         * @param buffer    puntero al primer byte donde debe escribirse
         * @return cantidad de bytes usados
         */
        virtual int serialize(char* buffer) = 0;
        /**
         * @brief hidratación
         * @param buffer    puntero al byte donde empieza sus datos
         * @return cantidad de bytes leídos
         */
        virtual int deserialize(const char* buffer) = 0;
};

#endif  // __SERIALIZABLE_H__
