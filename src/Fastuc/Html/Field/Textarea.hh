<?hh // strict
namespace Fastuc\Html\Field;

class Textarea extends \Fastuc\Html\Field
{
	private $el;

	public function __construct( $name, $value = null )
	{
		parent::__construct( $name, $value );

		$this->el = $this->doc->createElement( 'textarea' );
	}

	public function __toString()
	{
		$this->el->setAttribute( 'id', $this->name );
		$this->el->setAttribute( 'name', $this->name );

		if( null !== $this->class )
		{
			$this->el->setAttribute( 'class', $this->class );
		}

		// Workaround. Put an space otherwise the generated XML has no closing tag and the page breaks down.
		$valueNode = $this->doc->createTextNode( null === $this->value ? '' : $this->value );
		$this->el->appendChild( $valueNode );

		return $this->doc->saveXml( $this->el );
	}
}


