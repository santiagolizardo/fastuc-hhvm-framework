<?hh // strict
namespace Fastuc\Html\Field;

class Date extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'date', $name, $value );
	}
}

