import org.hibernate.*;
import org.hibernate.query.Query;
import org.hibernate.cfg.Configuration;

import javax.persistence.metamodel.EntityType;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Main {
    private static final SessionFactory ourSessionFactory;
    private static final Session session = getSession();

    static {
        try {
            Configuration configuration = new Configuration();
            configuration.configure();

            ourSessionFactory = configuration.buildSessionFactory();
        } catch (Throwable ex) {
            throw new ExceptionInInitializerError(ex);
        }
    }

    public static Session getSession() throws HibernateException {
        return ourSessionFactory.openSession();
    }

    private void sell(Product product, Invoice invoice) {
        product.addInvoice(invoice);
        invoice.addProduct(product);
        session.save(product);
        session.save(invoice);
    }

    public static void main(final String[] args) throws Exception {

        try {
            /*Scanner sc = new Scanner(System.in);
            String prodName = sc.nextLine();
            int unitsOnStock = sc.nextInt();
            Product newProduct = new Product(prodName, unitsOnStock);*/
            List<Product> products = new ArrayList<>();
            List<Supplier> suppliers = new ArrayList<>();
            products.add(new Product("ryz", 200));
            products.add(new Product("maslo", 45));
            products.add(new Product("makaron", 129));
            products.add(new Product("woda", 1000));
            products.add(new Product("sok", 23));
            suppliers.add(new Supplier("Jana Pawla 2", "New York"));
            suppliers.add(new Supplier("Czarnowiejska", "Krakow"));
            suppliers.add(new Supplier("Widokowa", "Busan"));
            suppliers.get(0).addProduct(products.get(2));
            suppliers.get(1).addProduct(products.get(4));
            suppliers.get(1).addProduct(products.get(3));
            suppliers.get(2).addProduct(products.get(1));
            suppliers.get(2).addProduct(products.get(0));

            List<Category> categories = new ArrayList<>();
            categories.add(new Category("napoj"));
            categories.add(new Category("jedzenie"));
            products.get(0).setCategory(categories.get(0));
            products.get(1).setCategory(categories.get(0));
            products.get(2).setCategory(categories.get(0));
            products.get(3).setCategory(categories.get(1));
            products.get(4).setCategory(categories.get(1));



            Transaction transaction = session.beginTransaction();
            suppliers.forEach(session::save);
            products.forEach(session::save);
            categories.forEach(session::save);

            session.flush();
            session.clear();

            //Category drinks = session.get(Category.class, 9);
            //List<Product> pDrinks = drinks.getProducts();
            //pDrinks.forEach(System.out::println);

            Product rice = session.get(Product.class, 4);
            System.out.println(rice.getCategory().getName());

            transaction.commit();

        } finally {
            session.close();
        }
    }
}