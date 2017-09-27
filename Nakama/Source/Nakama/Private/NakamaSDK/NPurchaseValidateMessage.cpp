/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "NPurchaseValidateMessage.h"

namespace Nakama {

	NPurchaseValidateMessage::NPurchaseValidateMessage(std::string productId, std::string receiptData)
	{
		auto purchase = envelope.mutable_purchase()->apple_purchase();
		purchase.set_product_id(productId);
		purchase.set_receipt_data(receiptData);
	}

	NPurchaseValidateMessage::NPurchaseValidateMessage(std::string productId, std::string productType, std::string purchaseToken)
	{
		auto purchase = envelope.mutable_purchase()->google_purchase();
		purchase.set_product_id(productId);
		purchase.set_product_type(productType);
		purchase.set_purchase_token(purchaseToken);
	}

}
