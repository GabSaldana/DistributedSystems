
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Stack;

public class MaquinaDePila {
    
    private int contadorDePrograma;
    private ArrayList  memoria;
    private Stack pila;
    private TablaDeSimbolos tabla;
    private boolean stop = false;
    private boolean returning = false;
    private Stack<Marco> pilaDeMarcos;
    
    public MaquinaDePila(TablaDeSimbolos tabla){
        contadorDePrograma = 0;
        memoria = new ArrayList<Method>();
        pila = new Stack();
        this.tabla = tabla;
        pilaDeMarcos = new Stack();
    }
    
    public int numeroDeElementos(){
        return memoria.size() + 1;
    }
    
    //Funciones que se escriben en memoria
    public int agregarOperacion(String nombre){
        int posicion = memoria.size();
        try{
            memoria.add(this.getClass().getDeclaredMethod(nombre, null));
            return posicion;
        }
        catch(Exception e ){
            System.out.println("Error al agregar operación " + nombre + ". ");
        }
        return -1;
    }
    
    public int agregar(Object objeto){
        int posicion = memoria.size();
        memoria.add(objeto);
        return posicion;
    }
    
    public void agregar(Object objeto, int posicion){
        memoria.remove(posicion);
        memoria.add(posicion, objeto);
    }
    
    public int agregarOperacionEn(String nombre, int posicion){
        try{
            memoria.add(posicion, this.getClass().getDeclaredMethod(nombre, null));
        }
        catch(Exception e ){
            System.out.println("Error al agregar operación " + nombre + ". ");
        }
        return posicion;
    }
    
    //Funciones que la máquina ejecuta sobre la pila
    private void sumar(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        if(matriz1 instanceof Matriz && matriz2 instanceof Matriz)
            pila.push(MtrxOp.suma((Matriz)matriz1, (Matriz)matriz2));
        else 
            pila.push((double)matriz1 + (double)matriz2);
    }
    
    private void restar(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        if(matriz1 instanceof Matriz && matriz2 instanceof Matriz)
            pila.push(MtrxOp.resta((Matriz)matriz1, (Matriz)matriz2));
        else 
            pila.push((double)matriz1 - (double)matriz2);
    }

    private void multiplicar(){
        Object matriz2 = pila.pop();
        Object matriz1 = pila.pop();
        if(matriz1 instanceof Matriz && matriz2 instanceof Matriz)
            pila.push(MtrxOp.multiplicacion((Matriz)matriz1, (Matriz)matriz2));
        else 
            pila.push((double)matriz1 * (double)matriz2);
    }
    
    private void constPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    
    private void varPush(){
        pila.push(memoria.get(++contadorDePrograma));
    }
    
    private void varPush_Eval(){
        pila.push(tabla.encontrar((String)memoria.get(++contadorDePrograma)));
    }

    private void asignar(){
        String variable = (String)pila.pop();
        Object objeto = pila.pop();
        tabla.insertar(variable, objeto);
    }
    
    private void comparar(){
        Object A = pila.pop();
        Object B = pila.pop();
        if((A instanceof Matriz) && (B instanceof Matriz))
            pila.push(MtrxOp.comparar((Matriz)A, (Matriz)B));
        else
            pila.push((boolean)((double)A==(double)B));
    }

    private void compararNot(){
        Object A = pila.pop();
        Object B = pila.pop();
        if((A instanceof Matriz) && (B instanceof Matriz))
            pila.push(!MtrxOp.comparar((Matriz)A, (Matriz)B));
        else
            pila.push((double)A!=(double)B);
    }

    private void menor(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); //Se sacan en orden inverso por la forma de la pila
        if((A instanceof Matriz) && (B instanceof Matriz)){
            a = MtrxOp.sumaDeComponentes((Matriz)A);
            b = MtrxOp.sumaDeComponentes((Matriz)B);
        }            
        else{
            a = (double)A;
            b = (double)B;
        }
        pila.push(a < b);
    }

    private void mayor(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); //Se sacan en orden inverso por la forma de la pila
        if((A instanceof Matriz) && (B instanceof Matriz)){
            a = MtrxOp.sumaDeComponentes((Matriz)A);
            b = MtrxOp.sumaDeComponentes((Matriz)B);
        }            
        else{
            a = (double)A;
            b = (double)B;
        }
        pila.push(a > b);
    }

    private void menorIgual(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); //Se sacan en orden inverso por la forma de la pila
        if((A instanceof Matriz) && (B instanceof Matriz)){
            a = MtrxOp.sumaDeComponentes((Matriz)A);
            b = MtrxOp.sumaDeComponentes((Matriz)B);
        }            
        else{
            a = (double)A;
            b = (double)B;
        }
        pila.push(a <= b);
    }

    private void mayorIgual(){
        double a;
        double b;
        Object B = pila.pop();
        Object A = pila.pop(); //Se sacan en orden inverso por la forma de la pila
        if((A instanceof Matriz) && (B instanceof Matriz)){
            a = MtrxOp.sumaDeComponentes((Matriz)A);
            b = MtrxOp.sumaDeComponentes((Matriz)B);
        }            
        else{
            a = (double)A;
            b = (double)B;
        }
        pila.push(a >= b);
    }

    private void negar(){
        pila.push(! (boolean)pila.pop());
    }

    private void and(){
        pila.push((boolean)pila.pop() && (boolean)pila.pop());
    }

    private void or(){
        pila.push((boolean)pila.pop() || (boolean)pila.pop());
    }
    
    private void stop(){
        stop = true;
    }
    
    private void _return(){
        returning = true;
    }

    private void nop(){
    }
    
    private void _while(){
        int condicion = contadorDePrograma;
        boolean continua = true;
        while(continua && !returning){
            ejecutar(condicion + 3);           
            if((boolean)pila.pop()){ //lee el resultado de la condición de la pila
                ejecutar((int)memoria.get(condicion+1));//Ejecuta el cuerpo
            }
            else{
                contadorDePrograma = (int)memoria.get(condicion+2); 
                continua = false;
            }
        }     
    }
    
    private void _if_then_else(){
        int condicion = contadorDePrograma;
        ejecutar(condicion + 4); //Evalúa la condicion
        boolean resultado = true;
        try{
            resultado = (boolean)pila.pop();
        }
        catch(Exception e ){
        }
        if(resultado){ //lee el resultado de la condición de la pila
            ejecutar((int)memoria.get(condicion+1));//Ejecuta el cuerpo
        }
        else{
            ejecutar((int)memoria.get(condicion+2));
        }
        contadorDePrograma = (int)memoria.get(condicion+3) - 1; //El -1 es para corregir el aumento del cp al final de cada instrucción
    }

    private void _for(){
        int condicion = contadorDePrograma;
        ejecutar(condicion + 5);  // Ejecutamos la primera parte
        boolean continua = true;
        while(continua && !returning){
            ejecutar((int)memoria.get(condicion+1)); //evaluamos la condición        
            if((boolean)pila.pop()){ //lee el resultado de la condición de la pila
                ejecutar((int)memoria.get(condicion+3));//Ejecuta el cuerpo
                ejecutar((int)memoria.get(condicion+2));//Ejecuta la última parte del for
            }
            else{
                contadorDePrograma = (int)memoria.get(condicion+4); 
                continua = false;
            }
        } 
    }
    
    private void declaracion(){
        tabla.insertar((String)memoria.get(++contadorDePrograma), ++contadorDePrograma); //Apuntamos a la primera instrucción de la función
        int invocados = 0;
        while(memoria.get(contadorDePrograma) != null || invocados != 0){ //Llevamos cp hasta la siguiente instrucción después de la declaración
            if( memoria.get(contadorDePrograma) instanceof Method)
                if(((Method)memoria.get(contadorDePrograma)).getName().equals("invocar"))
                    invocados++;
            if(memoria.get(contadorDePrograma) == null)
                invocados--;
            contadorDePrograma++;
        }
    }
    
    private void invocar(){   
        Marco marco = new Marco();
        String nombre = (String)memoria.get(++contadorDePrograma);
        marco.setNombre(nombre);
        contadorDePrograma++;
        while(memoria.get(contadorDePrograma) != null){ //Aquí también usamos null como delimitador. Aquí se agregan los parámetros al marco
            if(memoria.get(contadorDePrograma) instanceof String){
                if(((String)(memoria.get(contadorDePrograma))).equals("Limite")){
                    Object parametro = pila.pop();
                    marco.agregarParametro(parametro);
                    contadorDePrograma++;
                }
            }
            else{ 
                ejecutarInstruccion(contadorDePrograma);
            }

        }
        marco.setRetorno(contadorDePrograma);
        pilaDeMarcos.add(marco);
        ejecutarFuncion((int)tabla.encontrar(nombre)); //VAMOS AQUI***************************
    }
    
    private void push_parametro(){
        pila.push(pilaDeMarcos.lastElement().getParametro((int)memoria.get(++contadorDePrograma)-1));
    }
    
    
    //Métodos para la ejecución
    public void printMemoria(){
        for(int i = 0; i < memoria.size(); i++)
            System.out.println("" + i + ": " +memoria.get(i));
    }
    
    public void ejecutar(){
        //printMemoria();
        stop = false;
        while(contadorDePrograma < memoria.size())
            ejecutarInstruccion(contadorDePrograma);
    }
    
    public void ejecutar(int indice){//ejecuta hasta que se encuentra Stop     
        contadorDePrograma = indice;
        while(!stop && !returning){
            ejecutarInstruccion(contadorDePrograma);
        }
        stop = false;
    }
    
    public void ejecutarFuncion(int indice){
        contadorDePrograma = indice;
        while(!returning && memoria.get(contadorDePrograma) != null){
            ejecutarInstruccion(contadorDePrograma);
        }
        returning = false;
        contadorDePrograma = pilaDeMarcos.lastElement().getRetorno();
        pilaDeMarcos.removeElement(pilaDeMarcos.lastElement());
    }
    
    public void ejecutarInstruccion(int indice){
        //System.out.println("Ejecutando: " + indice);
        try{         
            Object objetoLeido = memoria.get(indice);
            if(objetoLeido instanceof Method){
                Method metodo = (Method)objetoLeido;
                metodo.invoke(this, null);
            }
            if(objetoLeido instanceof Funcion){
                Funcion funcion = (Funcion)objetoLeido;
                pila.push(funcion.ejecutar(pila.pop()));
            }
            contadorDePrograma++;
        }
        catch(Exception e){}
    }
    
    public static class print implements Funcion{

        @Override
        public Object ejecutar(Object A) {
            System.out.println("");
            System.out.println("" + A);
            System.out.println("");
            return A;
        }

    }

    public static class invert implements Funcion{

        @Override
        public Object ejecutar(Object A) {
            Matriz invertida = MtrxOp.invierte((Matriz)A);
            return invertida;
        }
        
    }

    public static class sum implements Funcion{

        @Override
        public Object ejecutar(Object A) {
            return MtrxOp.sumaDeComponentes((Matriz)A);
        }
        
    }
    
    public static void main(String args[]) throws Exception{
        double[][] A = {{1,2},{3,4}};
        double[][] B = {{5,6},{7,8}};
        TablaDeSimbolos tablaLocal = new TablaDeSimbolos();
        Matriz matrizA = new Matriz(A);
        Matriz matrizB = new Matriz(B);
        Matriz matrizC = null;        
        MaquinaDePila maquina = new MaquinaDePila(tablaLocal);
        
        maquina.agregarOperacion("constPush");
        maquina.agregar(matrizA);
        maquina.agregarOperacion("varPush");
        maquina.agregar("var1");
        maquina.agregarOperacion("asignar");
        System.out.println("DECLARACIÓN var1");
        maquina.ejecutar();

        maquina.agregarOperacion("constPush");
        maquina.agregar(matrizB);
        maquina.agregarOperacion("varPush");
        maquina.agregar("var2");
        maquina.agregarOperacion("asignar");
        System.out.println("DECLARACIÓN var2");
        maquina.ejecutar();

        maquina.agregarOperacion("declaracion");
        maquina.agregar("funcion");
        int inicio = maquina.agregarOperacion("_if_then_else");
        maquina.agregarOperacion("stop");
        maquina.agregarOperacion("stop");
        maquina.agregarOperacion("stop");
        maquina.agregarOperacion("constPush");
        maquina.agregar(5.0);
        maquina.agregarOperacion("constPush");
        maquina.agregar(5.0);
        maquina.agregarOperacion("comparar");
        maquina.agregarOperacion("stop");
        int then_ = maquina.agregarOperacion("constPush");
        maquina.agregar(111.0);
        maquina.agregarOperacion("_return");
        int else_ = maquina.agregarOperacion("constPush");
        maquina.agregar(0.0);
        maquina.agregar(new print());
        maquina.agregarOperacion("stop");
        int final_ = maquina.numeroDeElementos() - 2;
        maquina.agregar(then_, inicio + 1);
        maquina.agregar(else_, inicio + 2);
        maquina.agregar(final_, inicio + 3);
        maquina.agregarOperacion("varPush_Eval");
        maquina.agregar("var2");
        maquina.agregarOperacion("_return");
        maquina.agregarOperacion("push_parametro");
        maquina.agregar(1);
        maquina.agregar(new print());
        maquina.agregar(null);
        System.out.println("DECLARACIÓN DE LA FUNCIÓN");
        maquina.ejecutar();

        maquina.agregarOperacion("invocar");
        maquina.agregar("funcion");
        maquina.agregarOperacion("varPush_Eval");
        maquina.agregar("var1");
        maquina.agregarOperacion("varPush_Eval");
        maquina.agregar("var2");
        maquina.agregar(null);
        maquina.agregarOperacion("varPush");
        maquina.agregar("var3");      
        maquina.agregarOperacion("asignar");
        System.out.println("INVOCACIÓN DE LA FUNCIÓN");
        maquina.ejecutar();
        
        maquina.agregarOperacion("varPush_Eval");
        maquina.agregar("var3");
        maquina.agregar(new print());
        System.out.println("VERIFICACIÓN DEL RETURN.");
        maquina.ejecutar();
        
        maquina.printMemoria();
        
    }

}
