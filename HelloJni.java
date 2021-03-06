import java.util.Random;
import java.util.UUID;
import java.util.Date;

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
    public native void accessMethod();
    public native void accessStaticMethod();
    public native Date accessConstructor();
    public native String accessUTFChars(String str);
    public native void sortArray(int[] arr);
    public native String[] getStringArray(int size);
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
        hello.accessMethod();
        hello.accessStaticMethod();
        Date date = hello.accessConstructor();
        System.out.println("call from java time = " + date.getTime() + "");
        System.out.println("call from java get string from c: " + hello.accessUTFChars("深圳"));
        int[] arr = {5, 3, 8, 81, 0};
        hello.sortArray(arr);
        for(int i = 0; i < arr.length; i++){
            System.out.println(arr[i]);
        }
        String[] cstrs = hello.getStringArray(10);
        for(int j = 0; j < cstrs.length; j++) {
            System.out.println(cstrs[j]);
        }
    }

    public int getRandomInt(int max){
        int ret = new Random().nextInt(max);
        System.out.println("Called from java, ret = " + ret);
        return ret;
    }

    static String getUUID(){
        String uuid = UUID.randomUUID().toString();
        System.out.println("Called from java, uuid = " + uuid);
        return uuid;
    }
}
