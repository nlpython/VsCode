import java.util.Scanner;

public class test {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        System.out.println("**********");
        System.out.println("(票价十元):");
        int amount;
        amount = in.nextInt();
        System.out.println(amount >= 10);
    /*		if (amount >= 10) {
          System.out.println("找零 : " + (amount - 10));
        } else {
          
        }*/
        System.out.println("找零 : " + (amount - 10));
    }
}
