package com.marketplace.views;

import java.util.HashMap;
import java.util.Map;

import com.marketplace.controllers.ProductController;
import com.marketplace.controllers.UserController;
import com.marketplace.models.Product;
import com.marketplace.enums.ReasonType;
import com.marketplace.utils.InputReader;

public class ViewProduct extends Interface {
    private ProductController productController;
    private UserController userController;
    private Product product;

    public ViewProduct(Product product) {
        this.numberOfOptions = 3;

        this.productController = new ProductController();
        this.userController = new UserController();
        this.product = product;

        this.showProduct();
    }

    public void showOptions() {
        System.out.println("\nProduto");
        System.out.println("1 - Avaliar Produto");
        System.out.println("2 - Denunciar Vendedor do Produto");
        System.out.println("3 - Voltar\n");
    }

    public void handleOption(int option) {
        switch (option) {
            case 1:
                this.rateProduct();
                break;
            case 2:
                this.reportSeller();
                break;
            default:
                break;
        }
    }

    private void rateProduct() {
        InputReader reader = new InputReader(this.keyboard);
        HashMap<String, Object> result;
        String comment;
        float rating = -1.0f;

        System.out.print("\n");
        while ((Float.compare(rating, 0f) < 0) || (Float.compare(rating, 5f) > 0))
            rating = reader.readFloat("Avaliação");

        comment = reader.readString("Comentario");
        result = this.productController.rate(rating, comment, this.product);

        Product temp = (Product) result.get("product");
        if (temp == null) {
            System.out.println("Não foi possivel Avaliar o produto");
            for (Map.Entry<String, Object> entry : result.entrySet())
                System.out.println(entry.getValue());
        }

        System.out.println("");
        this.product.showDetails();
        this.showOptions();
    }

    private void reportSeller() {
        InputReader reader = new InputReader(this.keyboard);
        ReasonType reason;
        String description;

        System.out.print("\n");
        reason = reader.readEnum(ReasonType.class, "Razão");
        description = reader.readString("Descrição");

        this.userController.report(this.product.getSeller(), reason, description);
        System.out.println("\nVendedor denunciado com sucesso!");

        this.showOptions();
    }

    private void showProduct() {
        this.product.showDetails();
    }
}
