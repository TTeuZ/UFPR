package com.marketplace.models;

import java.util.ArrayList;
import java.util.Iterator;

import javax.json.JsonArray;
import javax.json.JsonObject;

import com.marketplace.enums.PaymentMethodType;

public class PaymentMethodList extends ArrayList<PaymentMethod> {
    public static PaymentMethodList jsonToList(JsonArray jsonArray) {
        PaymentMethodList paymentMethods = new PaymentMethodList();

        for (JsonObject jsonPaymentMethod : jsonArray.getValuesAs(JsonObject.class)) {
            String type = jsonPaymentMethod.getString("type");
            PaymentMethodType paymentMethodType = PaymentMethodType.valueOf(type);

            PaymentMethod paymentMethod = new PaymentMethod(paymentMethodType);
            paymentMethods.add(paymentMethod);
        }

        return paymentMethods;
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String result = "";

        Iterator<PaymentMethod> iterator = this.iterator();
        while (iterator.hasNext())
            result += "\n" + iterator.next().toString(level);

        return result;
    }
}