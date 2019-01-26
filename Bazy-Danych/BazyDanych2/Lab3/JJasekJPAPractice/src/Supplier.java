import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

@Entity
public class Supplier {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int dbID;

    private String street;
    private String city;

    @OneToMany(mappedBy = "supplier")
    private Set<Product> products;

    public Supplier() {
        products = new HashSet<>();
    }

    public Supplier(String street, String city) {
        this.street = street;
        this.city = city;
        this.products = new HashSet<>();
    }

    public void addProduct(Product product) {
        products.add(product);
        product.setSupplier(this);
    }
}
