public class HelloJni{
    static{
        System.loadLibrary("HelloJni");
    }
    public native static String getStringFromCStatic();
    public native String getStringFromCNonStatic();
    public String key = "key";
    public static int count = 5;
    public native String accessField();
    public native void accessStaticField();
    public static void main(String[] args){
        System.out.println(getStringFromCStatic());
        HelloJni hello = new HelloJni();
        System.out.println(hello.getStringFromCNonStatic());
        System.out.println("change before key: " + hello.key);
        hello.accessField();
        System.out.println("change after key: " + hello.key);
        System.out.println("change before count: " + count);
        hello.accessStaticField();
        System.out.println("change after count: " + count);
    }
}