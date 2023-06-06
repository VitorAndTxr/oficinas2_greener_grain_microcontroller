
typedef enum{
    INITIALIZING,
    IDLE,
    WORKINKG,
    CONFIGURING
}ModuleStateEnum;

struct DispenseTask{
    int module;
    int peso;
};


DispenseTask Order = { -1,-1 };

ModuleStateEnum CurrentState = INITIALIZING;

void HandleDispenseOrder(){

    Serial.print("Processando ");
    Serial.print(Order.peso);
    Serial.print(" no módulo ");
    Serial.println(Order.module+1);

    float balanceDistance = measureDistanceUS(UnitSensors[2]);
    float curretPeso = getCurrentWeight();

    Serial.println("Esperando recipiente");

    do{
          balanceDistance = measureDistanceUS(UnitSensors[2]);
          curretPeso = getCurrentWeight();
          delay(100);



    }while(((balanceDistance > 25) || (curretPeso<15)));

    Serial.println("Aguardando tara...");

    delay(3000);

    float tara = curretPeso;

    Serial.println("Iniciando...");

    do{
        gira(HORARIO, 10, delayPassosRapidos,UnitMotors[Order.module]);
        gira(ANTIHORARIO, 80, delayPassosRapidos,UnitMotors[Order.module]);
        curretPeso = getCurrentWeight();

    }while(curretPeso<(0.8*(tara + Order.peso)));


        do{
        gira(HORARIO, 5, delayPassosLentos,UnitMotors[Order.module]);
        gira(ANTIHORARIO, 40, delayPassosLentos,UnitMotors[Order.module]);
        curretPeso = getCurrentWeight();        

    }while(curretPeso<((tara + Order.peso)));

    Serial.println("Remova o recipiente");

    do{
        balanceDistance = measureDistanceUS(UnitSensors[2]);
        curretPeso = getCurrentWeight();
        delay(100);
    }while(((balanceDistance < 30) || (curretPeso>30)));

    Serial.println("Finalizado o atendimento");

    Order = { -1,-1 };
    
    CurrentState = IDLE;
}