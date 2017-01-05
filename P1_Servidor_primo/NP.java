public class NP{
	public static void main(String[] args) {
		System.out.println(isPrimo(4294967291L));
	}

	public static boolean isPrimo(long num) {
			for(long i=2;i<num;i++)
        		if(num%i==0)
            		return false;
    		return true;
	}
}