<?hh // strict
namespace Fastuc\Html\Field;

class Password extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'password', $name, $value );
	}
}

