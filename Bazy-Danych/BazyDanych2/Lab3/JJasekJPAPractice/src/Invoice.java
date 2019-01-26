import javax.persistence.*;
import java.util.Set;

@Entity
public class Invoice {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    private int invoiceNumber;
    private int quantity;

    @ManyToMany(mappedBy = "invoices")
    private Set<Product> products;

    public Invoice() {

    }

    public Invoice(int invoiceNumber, int quantity) {
        this.invoiceNumber = invoiceNumber;
        this.quantity = quantity;
    }

    public void addProduct(Product product) {
        products.add(product);
    }
}
