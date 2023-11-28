package com.marketplace.models;

import com.marketplace.enums.PaymentMethodType;

public class PaymentMethod {
    private PaymentMethodType type;

    public PaymentMethod(PaymentMethodType type) {
        this.type = type;
    }

    public PaymentMethodType getType() {
        return type;
    }

    public static String parsePaymentMethod(PaymentMethodType type) {
        switch (type) {
            case CASH:
                return "Dinheiro";
            case CREDIT_CARD:
                return "Crédito";
            case DEBIT_CARD:
                return "Débito";
            case PIX:
                return "Pix";
            default:
                return "";
        }
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String tabbing = "";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        return tabbing + PaymentMethod.parsePaymentMethod(this.type);
    }
}
