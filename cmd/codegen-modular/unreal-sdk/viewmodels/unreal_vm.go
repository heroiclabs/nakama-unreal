package viewmodels

import "heroiclabs.com/yacg/modules"

type UeParamViewModel struct {
	modules.ViewModel
	Name    string
	Type    string
	Comment string
}
